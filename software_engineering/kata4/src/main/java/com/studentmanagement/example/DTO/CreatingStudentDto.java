package com.studentmanagement.example.DTO;

public class CreatingStudentDto {
    public String firstName;
    public String lastName;

    public static Builder builder() {
        return new Builder();
    }

    public static class Builder {
        CreatingStudentDto creatingStudentDto = new CreatingStudentDto();

        public Builder() {}

        public Builder withFirstName(String firstName) {
            creatingStudentDto.firstName = firstName;
            return this;
        }

        public Builder withLastname(String lastName) {
            creatingStudentDto.lastName = lastName;
            return this;
        }

        public CreatingStudentDto build() {
            return creatingStudentDto;
        }

    }
}
