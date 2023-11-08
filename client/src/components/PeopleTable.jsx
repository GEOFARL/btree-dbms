import { useContext, useMemo } from 'react';
import { PeopleContext } from '../context/PeopleContextProvider';

const PeopleTable = () => {
  const { state } = useContext(PeopleContext);

  console.log(state);

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
          <button>Modify</button>
        </td>
      </tr>
    ));
  }, [state]);

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
