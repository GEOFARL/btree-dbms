import { Router } from 'express';
import { createPerson } from '../controllers/person.js';

const router = Router();

router.post('/create', createPerson);

export default router;
