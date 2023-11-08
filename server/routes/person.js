import { Router } from 'express';
import {
  createPerson,
  deletePerson,
  dropDB,
  generateData,
  getAll,
  getComparisons,
  modifyPerson,
  searchPerson,
} from '../controllers/person.js';

const router = Router();

router.post('/create', createPerson);
router.delete('/delete', deletePerson);
router.get('/getAll', getAll);
router.patch('/modify', modifyPerson);
router.get('/search', searchPerson);
router.post('/generateData', generateData);
router.delete('/dropDB', dropDB);
router.get('/getComparisons', getComparisons);

export default router;
