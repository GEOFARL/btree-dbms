import fs from 'fs';

import { runProgram, runProgramSync } from '../config/cppApp.js';
import generatePerson from '../utils/generatePerson.js';

let cachedPeople;

// @desc    Create a new person
// @route   POST /api/person/create
// @access  Public
export const createPerson = (req, res) => {
  const { firstName, lastName, city, age } = req.body;
  const program = runProgram(['insert', firstName, lastName, city, age]);
  let newPerson = {};

  program.stdout.on('data', (chunk) => {
    console.log('Output:');
    const data = chunk
      .toString()
      .replace('Inserted: ', '')
      .replace(/\n/g, '')
      .trim();
    const [id, firstName, lastName, city, age] = data.split(',');
    newPerson = { id, firstName, lastName, city, age };
    console.log(newPerson);
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    res.status(201).send(newPerson);
  });
};

// @desc    Delete an existing person
// @route   DELETE /api/person/delete
// @access  Public
export const deletePerson = (req, res) => {
  const { firstName } = req.body;

  const program = runProgram(['remove', firstName]);

  program.stdout.on('data', (chunk) => {
    console.log('Output:');
    console.log(chunk.toString());
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    res.send({ firstName });
  });
};

// @desc    Retrieve all people data
// @route   GET /api/person/getAll
// @access  Public
export const getAll = async (req, res) => {
  return new Promise((resolve) => {
    const program = runProgram(['print']);
    const response = [];

    program.stdout.on('data', (chunk) => {
      const data = chunk
        .toString()
        .replace('Printing values...', '')
        .replace('Done!', '')
        .split('\n')
        .filter((line) => line.trim() !== '')
        .map((line) => line.replace(/\n/g, '').trim());

      data.map((line) => {
        const [id, firstName, lastName, city, age] = line.split(',');
        response.push({ id, firstName, lastName, city, age });
      });
      console.log(response);
    });

    program.stderr.on('data', (data) => {
      console.log('Error:');
      console.error(data.toString());
    });

    program.on('close', (code) => {
      console.log(`Closed with code ${code}`);
      cachedPeople = response;
      res.send(response);
      resolve();
    });
  });
};

// @desc    Modify an existing person
// @route   PATCH /api/person/modify
// @access  Public
export const modifyPerson = (req, res) => {
  const { data, key } = req.body;
  const { id, firstName, lastName, city, age } = data;
  const program = runProgram([
    'modify',
    key,
    id,
    firstName,
    lastName,
    city,
    age,
  ]);
  let response = {};

  program.stdout.on('data', (chunk) => {
    const data = chunk
      .toString()
      .replace('Modified: ', '')
      .replace(/\n/g, '')
      .trim();
    const [id, firstName, lastName, city, age] = data.split(',');
    response = { id, firstName, lastName, city, age };
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    console.log(response, 'response');
    res.send(response);
  });
};

// @desc    Search the person
// @route   GET /api/person/search
// @access  Public
export const searchPerson = (req, res) => {
  const searchKey = req.query.key;

  const program = runProgram(['search', searchKey]);
  let response = {};

  program.stdout.on('data', (chunk) => {
    if (chunk.toString().startsWith('Found:')) {
      const dataString = chunk.toString();
      const compIdx = dataString.indexOf('Comparisons: ');
      const comparisons = dataString
        .slice(compIdx)
        .replace('Comparisons: ', '')
        .replace(/\n/g, '')
        .trim();

      const data = dataString
        .slice(0, compIdx)
        .replace('Found: ', '')
        .replace(/\n/g, '')
        .trim();
      const [id, firstName, lastName, city, age] = data.split(',');
      response = { id, firstName, lastName, city, age, comparisons };
    }
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    console.log(response, 'response');
    res.send(response);
  });
};

// @desc    Generate a lot of entries
// @route   POST /api/person/generateData
// @access  Public
export const generateData = (req, res) => {
  const { number } = req.query;

  const people = [];

  for (let i = 0; i < number; i += 1) {
    const person = generatePerson();
    people.push(person);
    const { firstName, lastName, city, age } = person;
    runProgramSync(['insert', firstName, lastName, city, age]);
  }

  res.send(people);
};

// @desc    Drop DB
// @route   DELETE /api/person/dropDB
// @access  Public
export const dropDB = (req, res) => {
  const path = '/Users/geofarl/repos/dbms-b-trees/lab3/dbms/db/db.txt';
  if (fs.existsSync(path)) {
    fs.rmSync(path);
  }

  res.send({ status: 'DB dropped successfully' });
};

const getComparisonsForOneSearch = async (searchKey) => {
  return new Promise((resolve) => {
    const program = runProgram(['search', searchKey]);

    program.stdout.on('data', (chunk) => {
      if (chunk.toString().startsWith('Found:')) {
        const dataString = chunk.toString();
        const compIdx = dataString.indexOf('Comparisons: ');
        const comparisons = dataString
          .slice(compIdx)
          .replace('Comparisons: ', '')
          .replace(/\n/g, '')
          .trim();
        resolve(comparisons);
      }
    });
  });
};

// @desc    Get an average number of comparisons
// @route   GET /api/person/getComparisons
// @access  Public
export const getComparisons = async (req, res) => {
  let totalComparisons = 0;
  for (let i = 0; i < 10; i += 1) {
    if (!cachedPeople) {
      await getAll();
    }
    const searchKey =
      cachedPeople[Math.floor(Math.random() * cachedPeople.length)].firstName;
    totalComparisons += +(await getComparisonsForOneSearch(searchKey));
  }
  res.send({ comparisons: Math.ceil(totalComparisons / 10) });
};
