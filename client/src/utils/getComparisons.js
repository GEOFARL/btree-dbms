export default async function getComparisons() {
  const response = await fetch(
    'http://localhost:8000/api/person/getComparisons'
  );
  const data = await response.json();
  return data.comparisons;
}
