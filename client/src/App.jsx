import { useState } from 'react';
import AddForm from './components/AddForm';
import ControlPanel from './components/ControlPanel';
import PeopleTable from './components/PeopleTable';
import RemoveForm from './components/RemoveForm';
import SearchBox from './components/SearchBox';
import LoadingScreen from './components/LoadingScreen';

function App() {
  const [loading, setIsLoading] = useState(false);

  return (
    <>
      <div className="app">
        <ControlPanel setIsLoading={setIsLoading} />
        <div className="centered">
          <AddForm />
          <RemoveForm />
          <SearchBox />
          <PeopleTable />
        </div>
      </div>
      {loading && <LoadingScreen />}
    </>
  );
}

export default App;
