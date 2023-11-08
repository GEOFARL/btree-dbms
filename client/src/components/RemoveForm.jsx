import { useState } from 'react';

const RemoveForm = () => {
  const [firstName, setFirstName] = useState('');
  const [error, setError] = useState(null);
  const [submitted, setSubmitted] = useState(false);

  const handleSubmit = async (e) => {
    e.preventDefault();
    setSubmitted(true);

    if (firstName.trim().length === 0) {
      setError('First name cannot be empty');
      return;
    } else {
      setError(null);
    }

    setFirstName('');

    try {
      const response = await fetch('http://localhost:8000/api/person/delete', {
        method: 'DELETE',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ firstName }),
      });
      console.log(response);
    } catch (err) {
      console.error(err);
    }
  };

  return (
    <form className="form" onSubmit={handleSubmit}>
      <h2 className="form__heading">Remove person</h2>

      <div className="form-control">
        <label htmlFor="firstName">First Name: </label>
        <input
          type="text"
          id="firstName"
          value={firstName}
          onChange={(e) => {
            setFirstName(e.target.value);
            if (submitted && e.target.value.trim().length === 0) {
              setError('First name cannot be empty');
            } else {
              setError(null);
            }
          }}
        />

        {error && <p className="form__error">{error}</p>}
      </div>

      <button className="form__button">Remove</button>
    </form>
  );
};

export default RemoveForm;
