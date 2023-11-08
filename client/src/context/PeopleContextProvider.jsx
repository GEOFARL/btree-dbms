import { createContext, useEffect, useReducer } from 'react';
import peopleReducer from './peopleReducer';

export const PeopleContext = createContext();

// eslint-disable-next-line
const PeopleContextProvider = ({ children }) => {
  const [state, dispatch] = useReducer(peopleReducer, []);

  useEffect(() => {
    const abortController = new AbortController();

    const fetchData = async () => {
      try {
        const response = await fetch(
          'http://localhost:8000/api/person/getAll',
          {
            signal: abortController.signal,
          }
        );

        const data = await response.json();

        dispatch({ type: 'SET_PEOPLE', payload: data });
      } catch (err) {
        console.error(err);
      }
    };

    fetchData();

    return () => {
      abortController.abort();
    };
  }, []);

  return (
    <PeopleContext.Provider value={{ state, dispatch }}>
      {children}
    </PeopleContext.Provider>
  );
};

export default PeopleContextProvider;
