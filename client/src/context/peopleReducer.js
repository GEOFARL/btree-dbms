export default function peopleReducer(state, action) {
  switch (action.type) {
    case 'ADD_PERSON': {
      return [
        ...state,
        {
          ...action.payload,
        },
      ];
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

    case 'SET_PEOPLE': {
      return action.payload;
    }
  }
}
