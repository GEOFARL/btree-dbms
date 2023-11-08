import { Router } from 'express';
import { createPerson, deletePerson } from '../controllers/person.js';

const router = Router();

router.post('/create', createPerson);
router.delete('/delete', deletePerson);

export default router;
