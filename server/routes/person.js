import { Router } from 'express';
import {
  createPerson,
  deletePerson,
  getAll,
  modifyPerson,
} from '../controllers/person.js';

const router = Router();

router.post('/create', createPerson);
router.delete('/delete', deletePerson);
router.get('/getAll', getAll);
router.patch('/modify', modifyPerson);

export default router;
