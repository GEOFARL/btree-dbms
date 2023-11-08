import { useEffect, useMemo, useState } from 'react';

const PeopleTable = () => {
  const [peopleData, setPeopleData] = useState(null);

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

        console.log(data);

        setPeopleData(data);
      } catch (err) {
        console.error(err);
      }
    };

    fetchData();

    return () => {
      abortController.abort();
    };
  }, []);

  const content = useMemo(() => {
    if (!peopleData) return null;
    return peopleData.map((entry) => (
      <tr key={entry.id}>
        <td>{entry.id}</td>
        <td>{entry.firstName}</td>
        <td>{entry.lastName}</td>
        <td>{entry.city}</td>
        <td>{entry.age}</td>
      </tr>
    ));
  }, [peopleData]);

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
          </tr>
        </thead>
        <tbody>{content}</tbody>
      </table>
    </>
  );
};

export default PeopleTable;
