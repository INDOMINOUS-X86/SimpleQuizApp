#include <wx/wx.h>
#include <vector>
#include <iostream>
using namespace std;

class QuizApp : public wxApp {
public:
    virtual bool OnInit();
};

class QuizFrame : public wxFrame {
public:
    QuizFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    wxStaticText* questionText;
    vector<wxRadioButton*> optionRadios;
    wxButton* nextButton;

    // Added variables
    int currentQuestionIndex;
    int userScore;
    vector<wxString> questions;
    vector<vector<wxString>> answerOptions;
    vector<int> correctAnswerIndices;

    void OnNext(wxCommandEvent& event);
};

wxIMPLEMENT_APP(QuizApp);

bool QuizApp::OnInit() {
    QuizFrame* frame = new QuizFrame("Quiz App", wxPoint(50, 50), wxSize(400, 300));
    frame->Show(true);
    return true;
}

QuizFrame::QuizFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), currentQuestionIndex(0), userScore(0) {

    questions.push_back("What is the capital of France?");
    answerOptions.push_back({ "Berlin", "Paris", "London" });
    correctAnswerIndices.push_back(1);

    questions.push_back("Which programming language is this app written in?");
    answerOptions.push_back({ "C", "Java", "C++" });
    correctAnswerIndices.push_back(2);

    questions.push_back("What is 2 + 2?");
    answerOptions.push_back({ "3", "4", "5" });
    correctAnswerIndices.push_back(1);

    questionText = new wxStaticText(this, wxID_ANY, questions[currentQuestionIndex], wxPoint(10, 10));

    for (size_t i = 0; i < answerOptions[currentQuestionIndex].size(); ++i) {
        wxRadioButton* radio = new wxRadioButton(this, wxID_ANY, answerOptions[currentQuestionIndex][i],
            wxPoint(10, 50 + i * 30));
        optionRadios.push_back(radio);
    }

    nextButton = new wxButton(this, wxID_ANY, "Next", wxPoint(10, 50 + answerOptions[currentQuestionIndex].size() * 30));
    nextButton->Bind(wxEVT_BUTTON, &QuizFrame::OnNext, this);
}

void QuizFrame::OnNext(wxCommandEvent& event) {
    int userAnswerIndex = -1;

    for (size_t i = 0; i < optionRadios.size(); ++i) {
        if (optionRadios[i]->GetValue()) {
            userAnswerIndex = i;
            break;
        }
    }

    if (userAnswerIndex == correctAnswerIndices[currentQuestionIndex]) {
        userScore++;
    }
    
    currentQuestionIndex++;
    if (currentQuestionIndex < questions.size()) {
        questionText->SetLabel(questions[currentQuestionIndex]);

        for (size_t i = 0; i < answerOptions[currentQuestionIndex].size(); ++i) {
            optionRadios[i]->SetLabel(answerOptions[currentQuestionIndex][i]);
            optionRadios[i]->SetValue(false);
        }
    }
    else {
        wxMessageBox("Quiz completed! Your score: " + wxString::Format("%d", userScore));
        Close();
    }
}
