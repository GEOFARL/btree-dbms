import AddForm from './components/AddForm';
import PeopleTable from './components/PeopleTable';
import RemoveForm from './components/RemoveForm';

function App() {
  return (
    <div className="centered">
      <AddForm />
      <RemoveForm />
      <PeopleTable />
    </div>
  );
}

export default App;
