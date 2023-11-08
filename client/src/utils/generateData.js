export default async function generateData(numberOfEntries) {
  const response = await fetch(
    `http://localhost:8000/api/person/generateData?number=${numberOfEntries}`,
    {
      method: 'POST',
    }
  );
  const data = await response.json();
  return data;
}
