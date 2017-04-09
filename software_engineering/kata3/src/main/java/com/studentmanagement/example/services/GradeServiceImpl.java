package com.studentmanagement.example.services;

import com.studentmanagement.example.models.Grade;
import com.studentmanagement.example.repositories.GradeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * Created by cristi on 10.04.17.
 */
@Service
public class GradeServiceImpl implements GradeService {

    @Autowired
    private GradeRepository grades;

    @Override
    public Grade save(Grade entity) {
        return grades.save(entity);
    }

    @Override
    public List<Grade> getAll() {
        return grades.findAll();
    }

    @Override
    public Grade getById(Long id) {
        return grades.findOne(id);
    }

    @Override
    public void delete(Long id) {
        grades.delete(id);
    }

    public List<Grade> getAllStudentGrades(Long studentId) {
        return grades.findByStudentId(studentId);
    }
}
