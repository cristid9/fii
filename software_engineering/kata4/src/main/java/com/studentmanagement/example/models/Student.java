package com.studentmanagement.example.models;

import javax.persistence.*;
import java.io.Serializable;
import java.util.List;

@Entity
@Table(name = "student")
public class Student implements Serializable{

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(nullable = false)
    private Long id;

    @Column(length = 50, nullable = false)
    private String firstName;

    @Column(length = 50, nullable = false)
    private String lastName;

    // E ok lazy-loading. Nu folosim prea des notele unui student, deci are sens
    // sa le incarcam atunci cand ne trebuie.
    @OneToMany(fetch = FetchType.LAZY, mappedBy = "student", cascade={CascadeType.ALL})
    private List<Grade> grades;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public List<Grade> getGrades() {
        return grades;
    }

    public void setGrades(List<Grade> grades) {
        this.grades = grades;
    }

    public static Builder builder() {
        return new Builder();
    }

    public static class Builder {
        Student student = new Student();

        public Builder() {

        }

        public Builder withFirstName(String firstName) {
            student.setFirstName(firstName);
            return this;
        }

        public Builder withLastName(String lastName) {
            student.setLastName(lastName);
            return this;
        }

        public Builder withId(Long id) {
            student.setId(id);
            return this;
        }

        public Student build() {
            return student;
        }
    }
}
