package com.studentmanagement.example.services;

import com.studentmanagement.example.models.Student;

import java.util.List;

public interface CrudService<T> {
    T save(T entity);
    List<T> getAll();
    T getById(Long id);
    void delete(Long id);
}
