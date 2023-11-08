import { useContext, useState } from 'react';
import dropDB from '../utils/dropDB.js';
import generateData from '../utils/generateData.js';
import { PeopleContext } from '../context/PeopleContextProvider.jsx';
import getComparisons from '../utils/getComparisons.js';

// eslint-disable-next-line
const ControlPanel = ({ setIsLoading }) => {
  const { dispatch } = useContext(PeopleContext);
  const [comparisons, setComparisons] = useState(null);

  const handleGenerateData = async () => {
    setIsLoading(true);
    const people = await generateData(1000);
    dispatch({ type: 'ADD_PEOPLE', payload: people });
    setIsLoading(false);
  };

  const handleDropDB = async () => {
    setIsLoading(true);
    await dropDB();
    dispatch({ type: 'SET_PEOPLE', payload: [] });
    setIsLoading(false);
  };

  const handleComparisons = async () => {
    setIsLoading(true);
    const comparisons = await getComparisons();
    setComparisons(comparisons);
    setIsLoading(false);
  };

  return (
    <div className="control-panel">
      <div className="content">
        <div>
          <button className="nav-button" onClick={handleGenerateData}>
            Generate Data
          </button>
          <button className="nav-button" onClick={handleDropDB}>
            Drop DB
          </button>
        </div>

        <div className="content__comparisons">
          {comparisons && <p>Comparisons: {comparisons}</p>}
          <button
            className="form__button modify-button"
            onClick={handleComparisons}
          >
            Get Comparisons
          </button>
        </div>
      </div>
    </div>
  );
};

export default ControlPanel;
