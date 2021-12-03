const express = require('express');
const router = express.Router();
const ObjectId = require('mongoose').Types.ObjectId;

const { user } = require('../models/user');

router.get('/api/users', (req, res) => {
    user.find({}, (err, data) => {
        if (!err) {
            res.send(data);
        } else {
            console.log(err);
        }
    });
});

router.post('/api/users/add', (req, res) => {
    const emp = new user({
        username: req.body.username,
        userRole: req.body.userRole,
        password: req.body.password
    });
    emp.save((err, data) => {
        res.status(200).json({
            code: 200, message: 'Successfully!',
            addUser: data
        })
    });
});

//Get Single user
router.get('/api/users/:id', (req, res) => {
    user.findById(req.params.id, (err, data) => {
        if (!err) {
            res.send(data);
        } else {
            console.log(err);
        }
    });
});

//Update user
router.patch('/api/users/edit/:id', (req, res) => {
    const emp = {
        username: req.body.username,
        userRole: req.body.userRole,
        password: req.body.password
    };
    user.findByIdAndUpdate(req.params.id, { $set: emp }, { new: true }
        , (err, data) => {
            if (!err) {
                res.status(200).json({
                    code: 200, message: 'Updated!',
                    updateUser: data
                })
            } else {
                console.log(err);
            }
        });
});

//Delete user
router.delete('/api/users/:id', (req, res) => {
    user.findByIdAndRemove(req.params.id, (err, data) => {
        if (!err) {
            res.status(200).json({
                code: 200, message: 'Deleted!',
                deleteUser: data
            })
        } else {
            console.log(err);
        }
    });
});

module.exports = router;
