const mongoose = require('mongoose');

const courseSchema = new mongoose.Schema(
    {
        name: {
            type: String,
            required: [true, 'Please provide the course name']
        },
        school_year_start: {
            type: Number,
            required: [true, 'Please provide the beginning school-year']
        },
        school_year_end: {
            type: Number,
            required: [true, 'Please provide the ending school-year']
        },
        term: {
            type: Number,
            enum: [1, 2],
            default: 1
        },
        leader: {
            type: mongoose.Schema.ObjectId,
            ref: 'User',
            required: [true, 'A course must have at least a leader']
        }
    },
    {
        toJSON: { virtuals: true },
        toObject: { virtuals: true }
    }
);

courseSchema.index({ course: 1, leader: 1 });
courseSchema.pre(/^find/, function (next) {
    this.populate({
        path: 'user',
        select: 'name photo'
    });
    next();
});

const Course = mongoose.model('Course', courseSchema);
module.exports = { Course };