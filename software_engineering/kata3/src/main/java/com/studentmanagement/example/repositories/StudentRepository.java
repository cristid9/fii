package com.studentmanagement.example.repositories;

import com.studentmanagement.example.models.Student;
import org.springframework.data.jpa.repository.JpaRepository;

public interface StudentRepository extends JpaRepository<Student, Long> {
}
