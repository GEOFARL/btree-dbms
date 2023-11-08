export default function modifyReducer(state, action) {
  switch (action.type) {
    case 'NO_MODIFY': {
      return {
        isModifying: false,
        entry: null,
      };
    }
    case 'SET_MODIFY': {
      return {
        isModifying: true,
        entry: action.payload,
      };
    }
  }
}
