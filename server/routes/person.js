import { Router } from 'express';
import { createPerson, deletePerson, getAll } from '../controllers/person.js';

const router = Router();

router.post('/create', createPerson);
router.delete('/delete', deletePerson);
router.get('/getAll', getAll);

export default router;
