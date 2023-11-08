export default async function dropDB() {
  await fetch('http://localhost:8000/api/person/dropDB', {
    method: 'DELETE',
  });
}
