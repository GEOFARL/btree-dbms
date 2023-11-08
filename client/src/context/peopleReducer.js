export default function peopleReducer(state, action) {
  switch (action.type) {
    case 'ADD_PERSON': {
      const people = [
        ...state,
        {
          ...action.payload,
        },
      ];
      people.sort((a, b) =>
        a.firstName.toLowerCase() < b.firstName.toLowerCase() ? -1 : 1
      );
      return people;
    }
    case 'REMOVE_PERSON': {
      let deleted = false;
      return state.filter((person) => {
        if (!deleted && person.firstName === action.payload) {
          deleted = true;
          return false;
        }
        return true;
      });
    }

    case 'MODIFY_PERSON': {
      console.log(action);
      let found = false;
      return state.map((person) => {
        if (!found && person.firstName === action.payload.firstName) {
          found = true;
          return action.payload;
        }
        return person;
      });
    }

    case 'SET_PEOPLE': {
      return action.payload;
    }
  }
}
