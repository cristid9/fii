package com.studentmanagement.example.services;

import com.studentmanagement.example.models.Grade;

import java.util.List;

public interface GradeService extends CrudService<Grade> {
      List<Grade> getGradesByStudentId(Long studentId);
}
