package com.studentmanagement.example.DTO;

public class StudentDto extends CreatingStudentDto {
    public Long id;

    public static Builder builder() {
        return new StudentDto.Builder();
    }

    public static class Builder extends CreatingStudentDto.Builder {
        StudentDto studentDto = new StudentDto();

        public Builder() {}

        public Builder withFirstName(String firstName) {
            studentDto.firstName = firstName;
            return this;
        }

        public Builder withLastname(String lastName) {
            studentDto.lastName = lastName;
            return this;
        }

        public Builder withId(Long id) {
            studentDto.id = id;
            return this;
        }

        public StudentDto build() {
            return studentDto;
        }
    }

}
