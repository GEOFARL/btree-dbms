import AddForm from './components/AddForm';
import PeopleTable from './components/PeopleTable';
import RemoveForm from './components/RemoveForm';
import SearchBox from './components/SearchBox';

function App() {
  return (
    <div className="app centered">
      <AddForm />
      <RemoveForm />
      <SearchBox />
      <PeopleTable />
    </div>
  );
}

export default App;
