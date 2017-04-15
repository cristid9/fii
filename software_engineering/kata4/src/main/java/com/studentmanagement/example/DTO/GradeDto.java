package com.studentmanagement.example.DTO;

public class GradeDto extends CreatingGradeDto{
    public Long id;


    public static Builder builder() {
        return new GradeDto.Builder();
    }

    public static class Builder extends CreatingGradeDto.Builder {
        GradeDto gradeDto = new GradeDto();

        public Builder() {}

        public Builder withRate(Integer rate) {
            gradeDto.rate = rate;
            return this;
        }

        public Builder withDescription(String description) {
            gradeDto.description = description;
            return this;
        }

        public Builder withId(Long id) {
            gradeDto.id = id;
            return this;
        }

        public GradeDto build() {
            return gradeDto;
        }
    }
}
