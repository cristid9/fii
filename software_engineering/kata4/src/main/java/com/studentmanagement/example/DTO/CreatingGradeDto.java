package com.studentmanagement.example.DTO;

public class CreatingGradeDto {
    public Integer rate;
    public String description;

    public static Builder builder() {
        return new Builder();
    }

    public static class Builder {
        CreatingGradeDto creatingGradeDto = new CreatingGradeDto();

        public Builder() {}

        public Builder withRate(Integer rate) {
            creatingGradeDto.rate = rate;
            return this;
        }

        public Builder withDescription(String description) {
            creatingGradeDto.description = description;
            return this;
        }

        public CreatingGradeDto build() {
            return creatingGradeDto;
        }
    }
}

