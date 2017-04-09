package com.studentmanagement.example.controllers;

import com.studentmanagement.example.models.Grade;
import com.studentmanagement.example.services.GradeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/v1/grades")
public class GradesController {

    @Autowired
    private GradeService gradeService;

    @RequestMapping(method = RequestMethod.GET)
    public ResponseEntity<List<Grade>> get(){
        List<Grade> grades = this.gradeService.getAll();
        if (grades.isEmpty()){
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        }
        return new ResponseEntity<>(grades, HttpStatus.OK);
    }

    @RequestMapping(method = RequestMethod.POST)
    public ResponseEntity<Grade> addGrade(@RequestBody Grade grade){
        if (grade.getValue() == null || grade.getCourse() == null || grade.getStudentId() == null) {
            return new ResponseEntity<>(HttpStatus.NOT_ACCEPTABLE); // defensive programming
        }

        Grade savedGrade = this.gradeService.save(grade);
        return new ResponseEntity<>(savedGrade, HttpStatus.CREATED);
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<Grade> getGradeById(@PathVariable("id") Long id) {
        Grade grade = this.gradeService.getById(id);
        if (grade == null) {
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        }
        return new ResponseEntity<>(grade, HttpStatus.OK);
    }

    @RequestMapping(value = "/delete/{id}", method = RequestMethod.POST)
    public ResponseEntity<Grade> delete(@PathVariable("id") Long id) {
        Grade grade = this.gradeService.getById(id);

        if (grade == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }

        this.gradeService.delete(id);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
}
