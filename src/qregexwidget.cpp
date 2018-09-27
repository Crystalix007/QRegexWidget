#include "qregexwidget.h"
#include "ui_qregexwidget.h"

#include <jpcre2.hpp>
#include <QPlainTextEdit>

#include <QRegularExpression>

QRegexWidget::QRegexWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QRegexWidget)
{
    ui->setupUi(this);
	connect(ui->matchButton, &QPushButton::clicked, this, &QRegexWidget::doMatch);
	connect(ui->matchedText, &QPlainTextEdit::textChanged, this, &QRegexWidget::clearMatches);
}

QRegexWidget::~QRegexWidget()
{
    delete ui;
}

void QRegexWidget::doMatch()
{
	if (ui->matchRegex->text().isEmpty())
	{
		ui->label->setText("Cannot use empty match");
		return;
	}
	
	using jp = jpcre2::select<char>;
	
	jp::Regex re{ ui->matchRegex->text().toStdString() };
	
	if (!re)
	{
		ui->label->setText("Invalid Regex");
		return;
	}
	
	std::string text{ ui->matchedText->toPlainText().toStdString() };
	jp::VecNum vecNum{};
	jp::VecNas vecNas{};
	jp::VecNtN vecNtN{};
	jpcre2::VecOff matchOff{};
	jpcre2::VecOff matchEndOff{};
	jp::RegexMatch match{};
	
	match = match.setRegexObject(&re)
				.setSubject(&text)
				.setNumberedSubstringVector(&vecNum)
				.setNamedSubstringVector(&vecNas)
				.setNameToNumberMapVector(&vecNtN)
				.setMatchStartOffsetVector(&matchOff)
				.setMatchEndOffsetVector(&matchEndOff);
	
	if (!this->ui->searchOptions->text().isEmpty())
		match.addModifier(this->ui->searchOptions->text().toStdString());
	
	size_t count = match.match();
	
	ui->label->setText(QString::number(count) + " matches");
	
	QString html{};
	size_t currPos = 0;
	
	for (size_t i = 0; i < matchOff.size(); i++)
	{
		html += QString::fromStdString(text.substr(currPos, matchOff[i] - currPos)).toHtmlEscaped();
		html += "<font color=\"#77f\">" + QString::fromStdString(text.substr(matchOff[i], matchEndOff[i] - matchOff[i])).toHtmlEscaped() + "</font>";
		currPos = matchEndOff[i];
	}
	
	html += QString::fromStdString(text.substr(currPos)).toHtmlEscaped();
	html.replace(QRegularExpression{ QString{ "\r?\n" } }, "<br />\n");
	
	ui->matchedText->clear();
	ui->matchedText->appendHtml(html);
	
	jp::RegexReplace rr{ &re };
	rr = rr.setSubject(text).setReplaceWith(ui->replaceRegex->text().toStdString());
	
	if (!this->ui->searchOptions->text().isEmpty())
		rr.setModifier(this->ui->searchOptions->text().toStdString());
	
	QString replaced = QString::fromStdString(rr.replace());
	
	ui->replacedText->setPlainText(replaced);
	matched = true;
}

void QRegexWidget::clearMatches()
{
	if (matched)
	{
		matched = false;
		ui->matchedText->setPlainText(ui->matchedText->toPlainText());
		ui->replacedText->clear();
		ui->label->setText("");
	}
}
