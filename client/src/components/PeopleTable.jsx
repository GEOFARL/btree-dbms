import { useContext, useMemo } from 'react';
import { PeopleContext } from '../context/PeopleContextProvider';
import { ModifyContext } from '../context/ModificationContextProvider';

const PeopleTable = () => {
  const { dispatch } = useContext(ModifyContext);
  const { state } = useContext(PeopleContext);

  const content = useMemo(() => {
    if (!state) return null;
    return state.map((entry) => (
      <tr key={entry.id}>
        <td>{entry.id}</td>
        <td>{entry.firstName}</td>
        <td>{entry.lastName}</td>
        <td>{entry.city}</td>
        <td>{entry.age}</td>
        <td>
          <button
            onClick={() => {
              dispatch({ type: 'SET_MODIFY', payload: entry });
            }}
            className="form__button modify-button"
          >
            Modify
          </button>
        </td>
      </tr>
    ));
  }, [state, dispatch]);

  return (
    <>
      <h2 className="table__heading">Human data table</h2>
      <table className="table">
        <thead>
          <tr>
            <th>ID</th>
            <th>First Name</th>
            <th>Last Name</th>
            <th>City</th>
            <th>Age</th>
            <th></th>
          </tr>
        </thead>
        <tbody>{content}</tbody>
      </table>
    </>
  );
};

export default PeopleTable;
