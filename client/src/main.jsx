import React from 'react';
import ReactDOM from 'react-dom/client';
import App from './App.jsx';
import './index.css';
import PeopleContextProvider from './context/PeopleContextProvider.jsx';
import ModificationContextProvider from './context/ModificationContextProvider.jsx';

ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <PeopleContextProvider>
      <ModificationContextProvider>
        <App />
      </ModificationContextProvider>
    </PeopleContextProvider>
  </React.StrictMode>
);
