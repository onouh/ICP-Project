#pragma once

#include <memory>
#include <stack>

#include "State.hpp"
using namespace std;
namespace ASU
{
	typedef unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		// Run at start of each loop in Game.cpp
		void ProcessStateChanges();

		StateRef& GetActiveState();

	private:
		stack<StateRef> _states;
		StateRef _newState;

		bool _isRemoving;
		bool _isAdding, _isReplacing;
	};
}