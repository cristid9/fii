package com.studentmanagement.example.models;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "grade")
public class Grade implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(nullable = false)
    private Long id;

    @Column(nullable = false)
    private Integer rate;

    @Column(nullable = true)
    private String description;

    @ManyToOne
    @JoinColumn(name = "student")
    private Student student;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Integer getRate() {
        return rate;
    }

    public void setRate(Integer rate) {
        this.rate = rate;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Student getStudent() {
        return student;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public static Builder builder() {
        return new Builder();
    }

    public static class Builder {
        Grade grade = new Grade();

        public Builder() {

        }

        public Builder withRate(Integer rate) {
            grade.setRate(rate);
            return this;
        }

        public Builder withDescription(String description) {
            grade.setDescription(description);
            return this;
        }

        public Builder withId(Long id) {
            grade.setId(id);
            return this;
        }

        public Grade build() {
            return grade;
        }
    }

}
