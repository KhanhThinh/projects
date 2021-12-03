const express = require('express');
const courseController = require('./../controllers/courseController');
const authController = require('./../controllers/authControllers');
const reviewRouter = require('./../routes/reviewRoutes');

const router = express.Router();

router.use('/:courseId/reviews', reviewRouter);

router
    .route('/')
    .get(courseController.getAllCourses)
    .post(
        authController.protect,
        authController.restrictTo('admin', 'leader'),
        courseController.createCourse
    );

router
    .route('/:id')
    .get(courseController.getCourse)
    .patch(
        authController.protect,
        authController.restrictTo('admin', 'leader'),
        courseController.updateCourse
    )
    .delete(
        authController.protect,
        authController.restrictTo('admin'),
        courseController.deleteCourse
    );

module.exports = router;