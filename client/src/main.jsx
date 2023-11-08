import React from 'react';
import ReactDOM from 'react-dom/client';
import App from './App.jsx';
import './index.css';
import PeopleContextProvider from './context/PeopleContextProvider.jsx';

ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <PeopleContextProvider>
      <App />
    </PeopleContextProvider>
  </React.StrictMode>
);
