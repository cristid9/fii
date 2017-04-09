package com.studentmanagement.example.controllers;

import com.studentmanagement.example.models.Grade;
import com.studentmanagement.example.models.Student;
import com.studentmanagement.example.repositories.GradeRepository;
import com.studentmanagement.example.services.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * Added defensive coding, completed methods and added support for grades management.
 */

@RestController
@RequestMapping("/v1/students")
public class StudentController {
    @Autowired
    private StudentService service;

    @Autowired
    private GradeRepository gradeService;

    @RequestMapping(method = RequestMethod.GET)
    public ResponseEntity<List<Student>> get(){
        List<Student> students = this.service.getAll();
        if (students.isEmpty()){
            return new ResponseEntity<List<Student>>(HttpStatus.NO_CONTENT);
        }
        return new ResponseEntity<List<Student>>(students, HttpStatus.OK);
    }

    @RequestMapping(method = RequestMethod.POST)
    public ResponseEntity<Student> addStudent(@RequestBody Student student){
        if (student.getFirstName().length() > 50 || student.getLastName().length() > 50) {
            return new ResponseEntity<Student>(HttpStatus.NOT_ACCEPTABLE); // defensive programming
        }

        Student savedStudent = this.service.save(student);
        return new ResponseEntity<Student>(savedStudent, HttpStatus.CREATED);
    }

    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public ResponseEntity<Student> getStudentById(@PathVariable("id") Long id) {
        Student student = this.service.getById(id);
        if (student == null) {
            return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
        }
        return new ResponseEntity<Student>(student, HttpStatus.OK);
    }

    @RequestMapping(value = "/delete/{id}", method = RequestMethod.POST)
    public ResponseEntity<Student> delete(@PathVariable("id") Long id) {
        Student student = this.service.getById(id);

        if (student == null) {
            return new ResponseEntity<Student>(HttpStatus.NOT_FOUND);
        }

        this.service.delete(id);
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
    }

    // normal ar fi trebuit fiecare operatie relatata unui serviciu sa fie in serviciul ei,
    // dar avand in vedere relatia dintre grade si student am adaugat o parte dintre ele
    // aici, odar pe cele foarte specifice pentru un student.

    @RequestMapping(value = "grades/{id}", method = RequestMethod.GET)
    public ResponseEntity<List<Grade>> getGrades(@PathVariable("id") Long id) {
        Student student = service.getById(id);

        if (student == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }

        List<Grade> grades = gradeService.findByStudentId(id);
        return new ResponseEntity<>(grades, HttpStatus.OK);
    }

    @RequestMapping(value = "grades/{course}/{id}", method = RequestMethod.GET)
    public ResponseEntity<List<Grade>> getGradesOnCourse(@PathVariable("id") Long id,
                                                         @PathVariable("course") String course) {
        Student student = service.getById(id);

        if (student == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }

        List<Grade> grades = gradeService.findByStudentIdAndCourse(id, course);
        return new ResponseEntity<>(grades, HttpStatus.OK);
    }

    @RequestMapping(value = "grades/add", method = RequestMethod.POST)
    public ResponseEntity<Grade> addGrade(@RequestBody Grade grade) {
        Student student = service.getById(grade.getStudentId());

        if (student == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }

        Grade savedGrade = gradeService.save(grade);
        return new ResponseEntity<>(grade, HttpStatus.OK);
    }
}
