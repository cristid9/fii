package com.studentmanagement.example.repositories;

import com.studentmanagement.example.models.Grade;
import org.springframework.data.jpa.repository.JpaRepository;

public interface GradeRepository extends JpaRepository<Grade, Long> {
}
