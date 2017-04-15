package com.studentmanagement.example.services;

import com.studentmanagement.example.models.Student;
import com.studentmanagement.example.repositories.StudentRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class StudentServiceImpl implements StudentService {
    @Autowired
    private StudentRepository repository;

    @Override
    public Student save(Student entity) {
        return this.repository.save(entity);
    }

    @Override
    public List<Student> getAll() {
        return this.repository.findAll();
    }

    @Override
    public Student getById(Long id) {
        return this.repository.findOne(id);
    }

    @Override
    public void delete(Long id) {
        this.repository.delete(id);
    }
}
