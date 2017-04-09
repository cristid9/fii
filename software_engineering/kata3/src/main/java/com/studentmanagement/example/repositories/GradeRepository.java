package com.studentmanagement.example.repositories;

import com.studentmanagement.example.models.Grade;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface GradeRepository extends JpaRepository<Grade, Long> {
    @Query(value = "select * from grade where sid = ?1", nativeQuery = true)
    List<Grade> findByStudentId(Long studentId);

    @Query(value = "select * from grade where sid = ?1 and course = ?2", nativeQuery = true)
    List<Grade> findByStudentIdAndCourse(Long studentId, String course);
}

