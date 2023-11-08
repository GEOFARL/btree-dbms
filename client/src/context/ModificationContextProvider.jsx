import { createContext, useReducer } from 'react';
import modifyReducer from './modifyReducer';

export const ModifyContext = createContext();

// eslint-disable-next-line
const ModificationContextProvider = ({ children }) => {
  const [state, dispatch] = useReducer(modifyReducer, {
    isModifying: false,
    entry: null,
  });

  return (
    <ModifyContext.Provider value={{ state, dispatch }}>
      {children}
    </ModifyContext.Provider>
  );
};

export default ModificationContextProvider;
