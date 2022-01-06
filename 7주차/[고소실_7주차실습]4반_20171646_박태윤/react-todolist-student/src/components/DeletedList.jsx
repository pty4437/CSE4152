import React from "react";
import styled from "styled-components";

import DeletedTodoItem from "./DeletedTodoItem";

// 인자로 받은 deletedTodos의 각 항목(삭제 항목) 객체를 가지고 DeletedTodoItem 컴포넌트를 생성해서 DELETED LIST 부분에 리스트로 보여줌
function DeletedList({ deletedTodos }) {

  return (
    <Container>
        <h1 style={{color: '#415e3e'}}>DELETED LIST</h1>
        <DeletedListContainer>
          {deletedTodos.map((todo) => {
            return <DeletedTodoItem todo={todo}/>
          })}
        </DeletedListContainer>
    </Container>
  );
  
}

// user custom components
const Container = styled.div`
  display: flex;
  flex-direction: column;
  width: 1200px;
  height: 400px;
  background-color: #fff;
`;

const DeletedListContainer = styled.div`
  display: flex;
  flex-direction: column;
  padding: 10px;
  margin: 20px 10px;
  height: 300px;
  overflow-y: scroll;
`;

export default DeletedList;
