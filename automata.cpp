#include "automata.h"
#include <iostream>

using namespace std;

/**
 * Constructor for Abstract DFA.
 * 
 * @param noStates
 *            Number of states in the DFA.
 */
AbstractDFA::AbstractDFA(int noStates) {
	nStates = noStates;
	currentState = 0;
	for (int &finalState : finalStates) finalState = 0;
	transitions = map<tpair, int>();
}

/**
 * Reset the automaton to the initial state.
 */
void AbstractDFA::reset() {
	currentState = 0;
}

/**
 * Performs one step of the DFA for a given letter. If there is a transition
 * for the given letter, then the automaton proceeds to the successor state.
 * Otherwise it goes to the sink state. By construction it will stay in the
 * sink for every input letter.
 * 
 * @param letter
 *            The current input.
 */

// UNICA FUNZIONE DEGNA DI NOTA. SONO 5 RIGHE IN CROCE PARLANTI E BANALI, NESSUN BISOGNO DI SPIEGARLE
void AbstractDFA::doStep(char letter) {
	const tpair tp = tpair(currentState, letter);
	const auto state = transitions.find(tp);
	const auto &value = (*state).first;
	if (value.second) currentState = state->second;
	else
		currentState = -1;
}

/**
 * Check if the automaton is currently accepting.
 * 
 * @return True, if the automaton is currently in the accepting state.
 */
bool AbstractDFA::isAccepting() {
	for (auto fs : finalStates) {
		if (fs == currentState) {
			return true;
		}
	}
	return false;
}

/**
 * Run the DFA on the input.
 * 
 * @param inputWord
 *            stream that contains the input word
 * @return True, if if the word is accepted by this automaton
 */
bool AbstractDFA::run(const string &inputWord) {
	for (char i : inputWord) {
		doStep(i);
		if (currentState == -1) {
			return false;
		}
	}
	return isAccepting();
}

void AbstractDFA::addFinalState(int node) {
	finalStates[0] = node;
}

void AbstractDFA::addTransition(int node, char input, int state) {
	transitions[tpair(node, input)] = state;
}

/**
 * Construct a new DFA that recognizes exactly the given word. Given a word
 * "foo" the constructed automaton looks like: -> () -f-> () -o-> () -o-> []
 * from every state (including the final one) every other input letter leads
 * to a distinguished sink state in which the automaton then remains
 * 
 * @param word
 *            A String that the automaton should recognize
 */
WordDFA::WordDFA(const string &word) : AbstractDFA(word.length()) {
	auto counter = 0;
	for (auto ch : word) {
		addTransition(counter, ch, counter + 1);
		counter++;
	}
	addFinalState(word.length());
}

/**
 * Construct a new DFA that recognizes comments within source code. There
 * are three kinds of comments:
 * single line comment that starts with // and ends with a newline,
 * multiline comments that starts with (* and ends with *), and
 * multiline comments that starts with { and ends with }
 */
CommentDFA::CommentDFA() : AbstractDFA(5) {
	addFinalState(777);
	addTransition(0, '/', 1);
	addTransition(1, '/', 2);
	addTransition(2, '\n', 777);
	addTransition(0, '(', 5);
	addTransition(5, '*', 6);
	addTransition(6, '*', 7);
	addTransition(7, ')', 777);
	addTransition(0, '{', 21);
	addTransition(21, '}', 777);
}

/**
 * Performs one step of the DFA for a given letter. This method works
 * differently than in the superclass AbstractDFA.
 * 
 * @param letter
 *            The current input.
 */


// CODICE MOLTO PARLANTE, NESSUN BISOGNO DI COMMENTARE DEI SEMPLICI IF ELSE
void CommentDFA::doStep(char letter) {
	switch (letter) {
		case '/':
			if (currentState == 5) currentState = -1;
			if (currentState == 7) currentState = 6;
			if (currentState == 0 || currentState == 1) {
				AbstractDFA::doStep(letter);
			}
			break;
		case '\n':
			if (currentState == 5) currentState = -1;
			if (currentState == 7) currentState = 6;
			if (currentState == 2) {
				AbstractDFA::doStep(letter);
			}
			break;
		case '*':
			if (currentState == 5 || currentState == 6) {
				AbstractDFA::doStep(letter);
			} else if (currentState == 7) {
				currentState = 7;
			} else
				currentState = -1;
			break;
		case '(':
			if (currentState == 5) currentState = -1;
			if (currentState == 7) currentState = 6;
			if (currentState == 0) {
				AbstractDFA::doStep(letter);
			} else if (currentState != 6)
				currentState = -1;
			break;
		case ')':
			if (currentState == 5) currentState = -1;
			if (currentState == 7 || currentState == 777) AbstractDFA::doStep(letter);
			break;
		case '{':
			if (currentState == 5) currentState = -1;
			if (currentState == 7) currentState = 6;
			if (currentState == 0) { AbstractDFA::doStep(letter); }
			break;
		case '}':
			if (currentState == 5) currentState = -1;
			if (currentState == 7) currentState = 6;
			else
				AbstractDFA::doStep(letter);
			break;
		default:
			if (currentState == 0 || currentState == 5) currentState = -1;
			if (currentState == 7) currentState = 6;
			if (currentState == 777) AbstractDFA::doStep(letter);
			break;
	}
}
