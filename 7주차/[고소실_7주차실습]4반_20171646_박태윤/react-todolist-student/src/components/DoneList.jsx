import React from "react";
import styled from "styled-components";

import TodoItem from "./TodoItem";

// 인자로 받은 doneTodos의 각 항목(삭제 항목) 객체를 가지고 TodoItem 컴포넌트를 생성해서 DONE LIST 부분에 리스트로 보여줌
function DoneList({ doneTodos, onRemove, onToggle }) {

  return (
    <Container>
        <h1 style={{color: '#415e3e'}}>DONE LIST</h1>
        <DoneListContainer>
          {doneTodos.map((todo) => {
            return <TodoItem todo={todo} key={todo.id} onRemove={onRemove} onToggle={onToggle}/>
          })}
        </DoneListContainer>
    </Container>
  );
  
}

// user custom components
const Container = styled.div`
  display: flex;
  flex-direction: column;
  width: 400px;
  height: 400px;
  background-color: #fff;
`;

const DoneListContainer = styled.div`
  display: flex;
  flex-direction: column;
  padding: 10px;
  margin: 20px 10px;
  height: 380px;
  overflow-y: scroll;
`;

export default DoneList;
