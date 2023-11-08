import AddForm from './components/AddForm';
import ControlPanel from './components/ControlPanel';
import PeopleTable from './components/PeopleTable';
import RemoveForm from './components/RemoveForm';
import SearchBox from './components/SearchBox';

function App() {
  return (
    <div className="app">
      <ControlPanel />
      <div className="centered">
        <AddForm />
        <RemoveForm />
        <SearchBox />
        <PeopleTable />
      </div>
    </div>
  );
}

export default App;
