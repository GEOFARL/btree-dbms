import { useContext } from 'react';
import dropDB from '../utils/dropDB.js';
import generateData from '../utils/generateData.js';
import { PeopleContext } from '../context/PeopleContextProvider.jsx';

// eslint-disable-next-line
const ControlPanel = ({ setIsLoading }) => {
  const { dispatch } = useContext(PeopleContext);

  const handleGenerateData = async () => {
    setIsLoading(true);
    const people = await generateData(10000);
    dispatch({ type: 'ADD_PEOPLE', payload: people });
    setIsLoading(false);
  };

  const handleDropDB = async () => {
    setIsLoading(true);
    await dropDB();
    dispatch({ type: 'SET_PEOPLE', payload: [] });
    setIsLoading(false);
  };

  return (
    <div className="control-panel">
      <div className="content">
        <button className="nav-button" onClick={handleGenerateData}>
          Generate Data
        </button>
        <button className="nav-button" onClick={handleDropDB}>
          Drop DB
        </button>
      </div>
    </div>
  );
};

export default ControlPanel;
