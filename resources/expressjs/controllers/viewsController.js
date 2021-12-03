const { User } = require('../models/user');
const { Course } = require('../models/course');
const catchAsync = require('../utils/catchAsync');
const AppError = require('../utils/appError');

exports.getOverview = catchAsync(async (req, res, next) => {
    const courses = await Course.find();

    res.status(200).render('overview', {
        title: 'All Courses',
        courses
    });
});

exports.getCourse = catchAsync(async (req, res, next) => {
    const course = await Course.findOne({ slug: req.params.slug }).populate({
        path: 'reviews',
        fields: 'review rating user'
    });

    if (!course) {
        return next(new AppError('There is no course with this name', 404));
    }


    req.status(200).render('course', {
        title: `${course.name}`,
        course
    });
});

exports.getLoginForm = (req, res) => {
    res.status(200).render('login', {
        title: 'Log into your account'
    });
};

exports.getAccount = (req, res) => {
    res.status(200).render('account', {
        title: 'Your account'
    });
};

exports.getMyCourses = catchAsync(async (req, res, next) => {

});

exports.updateUserData = catchAsync(async (req, res, next) => {
    const updatedUser = await User.findByIdAndUpdate(
        req.user.id,
        {
            name: req.body.name,
            email: req.body.email
        },
        {
            new: true,
            runValidators: true
        }
    );

    res.status(200).render('account', {
        title: 'Your account',
        user: updatedUser
    });
});
