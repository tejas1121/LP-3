// SPDX-License-Identifier: MIT
pragma solidity ^0.8.20;

/// @title StudentData
/// @notice Stores student records using a struct, a dynamic array and a fallback function.
contract StudentData {
    // ---------- Structure ----------
    struct Student {
        uint256 rollNo;
        string name;
        uint8 age;
        string course;
    }

    // ---------- Array ----------
    Student[] public students;

    address public owner;

    // ---------- Events ----------
    event StudentAdded(uint256 indexed rollNo, string name);
    event FallbackCalled(address indexed sender, uint256 value, bytes data);

    constructor() {
        owner = msg.sender;
    }

    // Add a new student to the array
    function addStudent(
        uint256 _rollNo,
        string memory _name,
        uint8 _age,
        string memory _course
    ) public {
        students.push(Student(_rollNo, _name, _age, _course));
        emit StudentAdded(_rollNo, _name);
    }

    // Get a student by array index
    function getStudent(uint256 _index)
        public
        view
        returns (uint256, string memory, uint8, string memory)
    {
        require(_index < students.length, "Index out of range");
        Student memory s = students[_index];
        return (s.rollNo, s.name, s.age, s.course);
    }

    // Total number of students
    function getStudentCount() public view returns (uint256) {
        return students.length;
    }

    // Return the whole array
    function getAllStudents() public view returns (Student[] memory) {
        return students;
    }

    // ---------- Fallback ----------
    // Runs when a call is made with a function signature that does not exist,
    // or when Ether is sent together with unknown calldata.
    fallback() external payable {
        emit FallbackCalled(msg.sender, msg.value, msg.data);
    }

    // Runs when plain Ether is sent with empty calldata.
    receive() external payable {
        emit FallbackCalled(msg.sender, msg.value, "");
    }
}
