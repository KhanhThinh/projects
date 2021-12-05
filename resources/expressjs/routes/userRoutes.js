const express = require('express');
const userController = require('./../controllers/userControllers');
const authController = require('./../controllers/authControllers');

const router = express.Router();

router.post('/signup', authController.signup);
router.post('/login', authController.login);
router.get('/logout', authController.logout);

router.post('/forgot-pwd', authController.forgotPassword);
router.patch('/reset-pwd/:token', authController.resetPassword);

router.use(authController.protect);

router.patch('/update-pwd', authController.updatePassword);
router.get('/me', userController.getMe, userController.getUser);
router.patch('/updateMe',
    userController.uploadUserPhoto,
    userController.resizeUserPhoto,
    userController.updateMe);

router.delete('/deleteMe', userController.deleteMe);
router.use(authController.restrictTo('admin'));

router
    .route('/')
    .get(userController.getAllUsers)
    .post(userController.createUser);
router
    .route('/:id')
    .get(userController.getUser)
    .patch(userController.updateUser)
    .delete(userController.deleteUser);

module.exports = router;