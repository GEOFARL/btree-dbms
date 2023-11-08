import { useMemo, useState } from 'react';

const SearchBox = () => {
  const [key, setKey] = useState('');
  const [result, setResult] = useState(null);
  const [error, setError] = useState(null);
  const [submitted, setSubmitted] = useState(false);

  const handleSubmit = async (e) => {
    e.preventDefault();

    setSubmitted(true);

    if (key.trim().length === 0) {
      setError('Key cannot be empty');
      return;
    } else {
      setError(null);
    }

    try {
      const response = await fetch(
        `http://localhost:8000/api/person/search?key=${key}`
      );

      const data = await response.json();
      setResult(data);
    } catch (err) {
      console.error(err);
    }
  };

  const content = useMemo(() => {
    if (!result) return null;
    if (Object.keys(result).length !== 0) {
      return (
        <p>
          {result.id},{result.firstName},{result.lastName},{result.city},
          {result.age}
        </p>
      );
    } else {
      return <p>Not Found</p>;
    }
  }, [result]);

  return (
    <form className="form" onSubmit={handleSubmit}>
      <h2 className="form__heading">Search the person</h2>
      <div className="form-control">
        <label htmlFor="searchFirstName">Key (first name):</label>
        <input
          type="text"
          name="searchFirstName"
          id="searchFirstName"
          value={key}
          onChange={(e) => {
            setKey(e.target.value);
            if (result) setResult(null);
            if (submitted && e.target.value.trim().length === 0) {
              setError('Key cannot be empty');
              return;
            } else {
              setError(null);
            }
          }}
        />
        {error && <p className="form__error">{error}</p>}
      </div>

      {content}

      <button className="form__button">Search</button>
    </form>
  );
};

export default SearchBox;
