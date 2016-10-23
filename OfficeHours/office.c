//Developed my Camilo Rivera and Camilo Riviere
//This project is developed for practicing utilizing multithreading on a linux system with C , PTHREADS and using mutex
/*
This project involves a thread which represents a professor and has other threads which represent students. The user will have 2 input.
The 1st input is the amount of students at the office and the capacity of how many fit inside the professors office.
How to compile and run on Linux terminal system:
Step 1: Open the terminal and go to the working directory of the program.

Step 2: run this command “gcc –pthread –o part2 part2.c”

Step 3: run this command “./part 2 [# of students] [capacity of office]

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

void checkArgc(int argc);
int inputValidation(char *argv);
void executeThread(int val);
void checkPosixThreadFailure(int remoteConfiguration);

void *Professor();
void *Student(void *id);
void StartAnswer();
void AnswerComplete();
void StudentEntersOffice(int id);
void StudentLeavesOffice(int id);
void StartQuestion(int id);
void QuestionComplete(int id);

int studentsInside = 0;
int officeLimit = 0;
int nextQuestionId = 0;
int studentsWaiting = 0;

pthread_mutex_t office_mutex;
pthread_mutex_t student_mutex;
pthread_mutex_t professor_mutex;
pthread_mutex_t student_question_mutex;

pthread_cond_t professor_complete_cv;
pthread_cond_t student_question_cv;
pthread_cond_t office_capacity_cv;

int studentCondition = 0;
int officeCondition = 0;
int professorCondition = 0;

int main(int argc, char **argv)
{
	checkArgc(argc);

	studentsWaiting = inputValidation(argv[1]);
	officeLimit = inputValidation(argv[2]);

	pthread_mutex_init(&office_mutex, NULL);
	pthread_mutex_init(&student_mutex, NULL);
	pthread_mutex_init(&professor_mutex, NULL);
	pthread_mutex_init(&student_question_mutex, NULL);

	pthread_cond_init(&professor_complete_cv, NULL);
	pthread_cond_init(&student_question_cv, NULL);
	pthread_cond_init(&office_capacity_cv, NULL);

	executeThread(studentsWaiting);

	return 0;
}

void executeThread(int val)
{
	pthread_t professorthr;
	pthread_t studentsThreads[val];
	int remoteConfiguration;
	int i;

	remoteConfiguration = pthread_create(&professorthr, NULL, Professor, NULL);
	checkPosixThreadFailure(remoteConfiguration);

	for (i = 0; i < val; i++) {
		remoteConfiguration = pthread_create(&studentsThreads[i], NULL, Student, (void *) i);
		checkPosixThreadFailure(remoteConfiguration);
	}

	remoteConfiguration = pthread_join(professorthr, NULL);
	checkPosixThreadFailure(remoteConfiguration);

	for (i = 0; i < val; i++) {
		remoteConfiguration = pthread_join(studentsThreads[i], NULL);
		checkPosixThreadFailure(remoteConfiguration);
	}
}

void checkPosixThreadFailure(int remoteConfiguration)
{
	if (remoteConfiguration) {
		printf("ERROR; return code from pthread is %d\n", remoteConfiguration);
		exit(EXIT_FAILURE);
	}
}

void *Professor()
{
	while (1) {
		pthread_mutex_lock(&professor_mutex);

		// Professor is waiting for a student to ask a question.
		// When signalled -> locks the professor mutex
		while (!studentCondition)
			pthread_cond_wait(&student_question_cv, &professor_mutex);
		studentCondition = 0;

		StartAnswer();
		AnswerComplete();

		// Professor has completed answering the question and now we signal the next student.
		professorCondition = 1;
		pthread_cond_signal(&professor_complete_cv);

		// The resource for professor is ready for another question.
		pthread_mutex_unlock(&professor_mutex);
	}
}

void *Student(void *arg)
{
	long id = (long) arg;

	pthread_mutex_lock(&office_mutex);
	// Student may enter the office if there is occupancy.
	if (studentsInside < officeLimit) {
		StudentEntersOffice(id);
	} else {	// Students must wait for space if there is no occupancy.
		while (!officeCondition)
			pthread_cond_wait(&office_capacity_cv, &office_mutex);
		officeCondition = 0;

		StudentEntersOffice(id);
	}
	pthread_mutex_unlock(&office_mutex);

	int questionNumber = id % 4 + 1;

	while (questionNumber > 0) {
		pthread_mutex_lock(&student_mutex);
		StartQuestion(id);

		// Signal the professor that a student has posed a question
		studentCondition = 1;
		pthread_cond_signal(&student_question_cv);

		pthread_mutex_lock(&student_question_mutex);

		// Wait for the professor to finish answering the question.
		while (!professorCondition)
			pthread_cond_wait(&professor_complete_cv, &student_question_mutex);
		professorCondition = 0;

		QuestionComplete(id);
		pthread_mutex_unlock(&student_question_mutex);

		pthread_mutex_unlock(&student_mutex);
		questionNumber--;
		sleep(1);	// Students must wait before posing an additional question.
	}
	StudentLeavesOffice(id);
}

void StartAnswer()
{
	printf("Professor has started to answer question for student: %d\n", 
			nextQuestionId);
}

void AnswerComplete()
{
	printf("Professor has completed answering the question for student: %d\n", 
		nextQuestionId);
}

void StudentEntersOffice(int id)
{
	printf("Student: %d has appeared in the office.\n", id);
	studentsInside++;
}

void StudentLeavesOffice(int id)
{
	pthread_mutex_lock(&office_mutex);
	printf("Student: %d has exited the office.\n", id);

	studentsInside--;
	studentsWaiting--;

	// If there are no more students present -> professor sleeps
	if (studentsWaiting == 0)
		exit(EXIT_SUCCESS);
	// Or if there is additional space available in the office -> signal the next student
	// Done is an insurance -> We have the option to signal without checking
	else if (studentsInside < officeLimit) {
		officeCondition = 1;
		pthread_cond_signal(&office_capacity_cv);
	}

	pthread_mutex_unlock(&office_mutex);
}

void StartQuestion(int id)
{
	// The next question has been posed and is attached to an id.
	nextQuestionId = id;
	printf("Student: %d has posed a question.\n", id);
}

void QuestionComplete(int id)
{
	printf("Student: %d has approved the professor's answer.\n", id);
}

void checkArgc(int argc)
{
	if (argc > 3 || argc < 3) {
		printf("Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}
}

int inputValidation(char *argv)
{
	char *endptr, *str;
	long val;

	str = argv;
	errno = 0;
	/* To distinguish success/failure after call */
	val = strtol(str, &endptr, 10);

	/* Check for various possible errors */
	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
		|| (errno != 0 && val == 0)) {
		perror("strtol");
		exit(EXIT_FAILURE);
	}

	if (endptr == str) {
		fprintf(stderr, "No further digits were found\n");
		exit(EXIT_FAILURE);
	}

	/* If we got here, strtol() successfully parsed a number */
	// printf("strtol() returned %ld\n", val);

	if (*endptr != '\0') {
		printf("Additional characters after number: %s\n", endptr);
		exit(EXIT_FAILURE);
	}

	if (val < 0) {
		printf("Value cannot be less than or equal to 0\n");
		exit(EXIT_FAILURE);
	}

	return val;
}
