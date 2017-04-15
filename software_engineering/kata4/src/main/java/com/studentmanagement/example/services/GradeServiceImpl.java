package com.studentmanagement.example.services;

import com.studentmanagement.example.models.Grade;
import com.studentmanagement.example.repositories.GradeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

@Service
public class GradeServiceImpl implements GradeService {
    @Autowired
    private GradeRepository repository;

    @Override
    public Grade save(Grade entity) {
        return this.repository.save(entity);
    }

    @Override
    public List<Grade> getAll() {
        return this.repository.findAll();
    }

    @Override
    public Grade getById(Long id) {
        return this.repository.findOne(id);
    }

    @Override
    public void delete(Long id) {
        this.repository.delete(id);
    }

    @Override
    public List<Grade> getGradesByStudentId(Long studentId) {
        Stream<Grade> grades = this.repository.findAll().stream();
        return grades.filter(x -> x.getStudent().getId() == studentId).collect(Collectors.toList());
    }
}
