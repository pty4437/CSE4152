import React from "react";
import styled from "styled-components";

// 삭제된 항목 객체 하나를 한 줄로 보여주기 위한 컴포넌트
function DeletedTodoItem({ todo }) {
  
  return (
    <Container>
      <Topic>
        {todo.text}
      </Topic>
    </Container>
  );
  
}

// user custom components
const Container = styled.div`
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-items: center;
  margin: 3px 0;
`;

const Topic = styled.p`
  display: flex;
  flex-direction: row;
  align-items: center;
  width: 330px;
  height: 30px;
  padding: 0 10px;
  margin: 0 10px;
  border: 0.8px solid #ccc;
  font-size: 14px;
`;

export default DeletedTodoItem;
